
pandoc -t slidy --metadata-file=metadata.yaml --top-level-division=section -s -o PackagingDeployment.html 01_goals.md 02_considerations.md 03_docker.md 04_ci_cd.md 05_tooling.md 
