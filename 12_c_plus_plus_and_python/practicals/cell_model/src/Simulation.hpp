#ifndef CELL_MODEL_SIMULATION
#define CELL_MODEL_SIMULATION

#include <random>
#include <unordered_set>
#include <vector>

#include "Functions.hpp"

class Point {
public:
  Point() : x(0.0), y(0.0) {}
  Point(const double x, const double y) : x(x), y(y) {}

  bool operator==(const Point &other) const {
    return other.x == x && other.y == y;
  }

  double x;
  double y;
};

struct PointHash {
public:
  using Coord = std::pair<int, int>;
  PointHash(const double size);

  int total_number_of_buckets() const;
  int number_of_buckets_along_side() const;
  int bucket_coordinate_to_index(const Coord &c) const;
  Coord point_to_bucket_coordinate(const Point &p) const;
  Coord add_offset_periodic(const Coord &c, const Coord &offset) const;
  int operator()(const Point &p) const;

private:
  int m_sqrt_n_buckets;
  double m_cutoff;
};

class Simulation {
public:
  Simulation(const std::vector<double> &x, const std::vector<double> &y,
             const double size, const double max_dt);

  void integrate(const double period);
  const std::vector<Point>& get_positions();

private:
  void boundaries(const double dt);
  void diffusion(const double dt);
  void interactions(const double dt);
  void step(const double dt);

  std::default_random_engine m_generator;
  std::normal_distribution<double> m_normal;
  double m_size;
  double m_max_dt;
  PointHash m_hash;
  std::vector<std::pair<int, int>> m_bucket_offsets;
  std::unordered_set<Point, PointHash> m_positions;
  std::vector<Point> m_next_positions;
};

#endif
