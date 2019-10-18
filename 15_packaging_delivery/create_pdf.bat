
pandoc -V geometry:margin=1.25in --metadata-file=metadata.yaml --top-level-division=section -o PackagingDeployment.pdf 01_goals.md 02_considerations.md 03_docker.md 04_ci_cd.md 05_tooling.md 
