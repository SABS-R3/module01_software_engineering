all: practical

lectures_dir = lectures
practicals_dir = practicals
projects_dir = projects
publish_dir = publish

reveal_command = "pandoc -f markdown$(extensions) -t revealjs -s ${reveal_options} $^ -o ${publish_dir}/$@.html"
syntax =--highlight-style pygments_custom.theme

intro:${lectures_dir}/intro.md
	pandoc -f markdown$(extensions) -t beamer ${syntax} $^ -V theme:metropolis -V aspectratio:169 -o ${publish_dir}/$@.pdf

lectures%:${lectures_dir}/lectures%.md
	pandoc -f markdown$(extensions) -t beamer ${syntax} $^ -V theme:metropolis -V aspectratio:169 -o ${publish_dir}/$@.pdf

project%:${projects_dir}/project%.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf

practical:${practicals_dir}/practical.md
	pandoc  -f markdown$(extensions) $(pdf_template) $^ -o ${publish_dir}/$@.pdf

clean:
	rm ${publish_dir}/*.pdf
