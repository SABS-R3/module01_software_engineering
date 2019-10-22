all: lectures_01_pybind11 practical lectures_02_parallel lectures_03_multiprocessing

lectures_dir = lectures
practicals_dir = practicals
projects_dir = projects
publish_dir = publish

reveal_command = "pandoc -f markdown$(extensions) -t revealjs -s ${reveal_options} $^ -o ${publish_dir}/$@.html"
syntax =--highlight-style pygments_custom.theme

intro:${lectures_dir}/intro.md
	pandoc -f markdown$(extensions) -t beamer ${syntax} $^ -V theme:metropolis -V aspectratio:169 -o ${publish_dir}/$@.pdf

lectures_03_multiprocessing: 
	cp ${lectures_dir}/lectures_03_multiprocessing.ipynb ${publish_dir}/

lectures%:${lectures_dir}/lectures%.md
	pandoc -f markdown$(extensions) -t beamer ${syntax} $^ -V theme:metropolis -V aspectratio:169 -o ${publish_dir}/$@.pdf

project%:${projects_dir}/project%.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf

practical:${practicals_dir}/practical.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf
	cp ${practicals_dir}/mandelbrot.cpp ${publish_dir}/

clean:
	rm ${publish_dir}/*.pdf
