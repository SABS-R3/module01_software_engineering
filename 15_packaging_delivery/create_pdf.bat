
pandoc -V geometry:margin=1.25in --metadata-file=metadata.yaml --top-level-division=section -o PackagingDeployment.pdf ^
 01_goals.md ^
 02_considerations01.md 02_considerations02.md 02_considerations03.md 02_considerations04.md ^
 03_docker.md 04_ci_cd.md ^
 04_ci_cd_examples01.md 04_ci_cd_examples02.md 04_ci_cd_examples03.md 04_ci_cd_examples04.md ^
 05_tooling.md 06_projects.md 
