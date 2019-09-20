#include "Simulation.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

PointHash::PointHash(const double size) {
  m_cutoff = 3 * size;
  m_sqrt_n_buckets = static_cast<int>(std::floor(1.0 / m_cutoff));
  m_cutoff = 1.0 / m_sqrt_n_buckets;
}

int PointHash::total_number_of_buckets() const {
  return std::pow(m_sqrt_n_buckets, 2);
}
int PointHash::number_of_buckets_along_side() const { return m_sqrt_n_buckets; }

int PointHash::bucket_coordinate_to_index(const Coord &c) const {
  return c.second * m_sqrt_n_buckets + c.first;
}
PointHash::Coord PointHash::point_to_bucket_coordinate(const Point &p) const {
  return std::make_pair(p.x / m_cutoff, p.y / m_cutoff);
}

PointHash::Coord PointHash::add_offset(const Coord &c,
                                       const Coord &offset) const {
  return std::make_pair(c.first + offset.first, c.second + offset.second);
}

bool PointHash::in_domain(const Coord &c) const {
  bool in_domain = true;
  if (c.first < 0 || c.first >= number_of_buckets_along_side()) {
    in_domain = false;
  }
  if (c.second < 0 || c.second >= number_of_buckets_along_side()) {
    in_domain = false;
  }
  return in_domain;
}

int PointHash::operator()(const Point &p) const {
  const Coord &coord = point_to_bucket_coordinate(p);
  const int bucket = bucket_coordinate_to_index(coord);
  assert(bucket < std::pow(m_sqrt_n_buckets, 2));
  assert(bucket > 0);
  return bucket;
}

Simulation::Simulation(const std::vector<double> &x,
                       const std::vector<double> &y, const double size,
                       const double max_dt, const size_t seed)
    : m_generator(seed), m_size(size), m_max_dt(max_dt), m_hash(size),
      m_positions(m_hash.total_number_of_buckets(), m_hash) {

  for (int i = 0; i < x.size(); ++i) {
    m_positions.insert(Point(x[i], y[i]));
  }

  m_next_positions.resize(m_positions.size());
  std::copy(m_positions.begin(), m_positions.end(), m_next_positions.begin());

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      m_bucket_offsets.push_back(std::make_pair(i, j));
    }
  }
}

void Simulation::boundaries(const double dt) {
  std::transform(m_next_positions.begin(), m_next_positions.end(),
                 m_next_positions.begin(), [](const Point &i) {
                   Point ret = i;
                   if (ret.x < 0.0) {
                     ret.x = 1.0 + ret.x;
                   } else if (ret.x > 1.0) {
                     ret.x = ret.x - 1.0;
                   }
                   if (ret.y < 0.0) {
                     ret.y = 1.0 + ret.y;
                   } else if (ret.y > 1.0) {
                     ret.y = ret.y - 1.0;
                   }
                   return ret;
                 });
}
void Simulation::diffusion(const double dt) {
  const double c = std::sqrt(2.0 * dt);
  std::transform(m_next_positions.begin(), m_next_positions.end(),
                 m_next_positions.begin(), [&](const Point &i) {
                   return Point(i.x + c * m_normal(m_generator),
                                i.y + c * m_normal(m_generator));
                 });
}

void Simulation::interactions(const double dt) {
  std::transform(
      m_next_positions.begin(), m_next_positions.end(),
      m_next_positions.begin(), [&](const Point &i) {
        const auto bucket_coords = m_hash.point_to_bucket_coordinate(i);
        return std::accumulate(
            m_bucket_offsets.begin(), m_bucket_offsets.end(), i,
            [&](const Point &sum, const auto &offset) {
              const auto other_bucket_coords =
                  m_hash.add_offset(bucket_coords, offset);
              if (!m_hash.in_domain(other_bucket_coords)) {
                return sum;
              }
              const int other_bucket =
                  m_hash.bucket_coordinate_to_index(other_bucket_coords);
              return std::accumulate(
                  m_positions.begin(other_bucket),
                  m_positions.end(other_bucket), sum,
                  [&](const Point &sum, const Point &j) {
                    Point ret = sum;
                    const double dx_x = i.x - j.x;
                    const double dx_y = i.y - j.y;
                    const double r =
                        std::sqrt(std::pow(dx_x, 2) + std::pow(dx_y, 2));
                    if (r > 0.0) {
                      const double tmp =
                          (dt / m_size) * std::exp(-r / m_size) / r;
                      ret.x += tmp * dx_x;
                      ret.y += tmp * dx_y;
                    }
                    return ret;
                  });
            });
      });
}

void Simulation::step(const double dt) {
  interactions(dt);
  diffusion(dt);
  boundaries(dt);

  m_positions.clear();
  m_positions.insert(m_next_positions.begin(), m_next_positions.end());
}
void Simulation::integrate(const double period) {
  const int n = static_cast<int>(std::floor(period / m_max_dt));
  std::cout << "integrating for " << n + 1 << " steps" << std::endl;
  for (int i = 0; i < n; ++i) {
    step(m_max_dt);
  }
  const double final_dt = period - m_max_dt * n;
  if (final_dt > 0) {
    step(final_dt);
  }
}
