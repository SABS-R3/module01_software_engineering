

# CI/CD: Concrete Examples

## CI/CD pipeline: Java package

Java package to be included and used by other applications. Concepts are not Java specific.

![Java package pipelines](JavaPackagePipeline.png)

![Detailed pipeline](JavaPackagePipelineDetailed.png)

* Build
  * Compile code
* Test
  * Run automated tests
  * CI/CD categorization of tests; fast vs slow
* Code analysis
  * Lint or code formatting
  * Static code analysis
  * Is the code clean?
  * Does the code possess recognizable bug, security, performance, etc patterns?
* Package
  * builds release artefacts - in this case the jar files for code, source code, and documentation
  * pushes release artefacts to artefact repository - our internal Nexus server
* Release pipeline (from Git tag) repeats everything in master pipeline - not ideal
  * mainly a limitation of the Java build tools which aren't very CD friendly 

\newpage
