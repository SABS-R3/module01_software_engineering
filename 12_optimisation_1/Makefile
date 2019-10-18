all: practical cell_model.zip publish_lectures

lectures_dir = lectures
practicals_dir = practicals
projects_dir = projects
publish_dir = publish
cell_model_dir = $(practicals_dir)/cell_model
cell_model_files = $(cell_model_dir)/README.md $(cell_model_dir)/setup.py $(cell_model_dir)/simulate.py $(cell_model_dir)/cell_model/__init__.py $(cell_model_dir)/cell_model/Simulation.py
lectures_files = $(lectures_dir)/lectures_00_numpy_vectorisation.ipynb $(lectures_dir)/lectures_01_cython.ipynb

reveal_command = "pandoc -f markdown$(extensions) -t revealjs -s ${reveal_options} $^ -o ${publish_dir}/$@.html"
syntax =--highlight-style pygments_custom.theme

intro:${lectures_dir}/intro.md
	pandoc -f markdown$(extensions) -t beamer ${syntax} $^ -V theme:metropolis -V aspectratio:169 -o ${publish_dir}/$@.pdf

publish_lectures: $(lectures_files)
	cp $(lectures_files) $(publish_dir)/

project%:${projects_dir}/project%.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf

cell_model.zip: $(cell_model_files)
	zip ${publish_dir}/cell_model.zip $(cell_model_files) 

practical:${practicals_dir}/practical.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf

clean:
	rm ${publish_dir}/*.pdf
