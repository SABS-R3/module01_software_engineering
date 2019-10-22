
# Considerations

*what* needs to be considered when planning how to release your software

## Modes of delivery

what is produced and distributed for a release

* Source code
  * Easy; just access to Git repository. 
  * Delivery process is to tag repository with release version.
  * A lot of effort for the user to use the code. 
  
* Library (binary) distribution
  * Distribution artefact is packaged binary code that is already compiled/built and ready for reuse
  * Used via language specific package system (e.g. import mechanism) 
    * Python and R; packages
    * Java; jar files
  * Key issues
    * how to specify what dependencies are needed by the distributed code
	* what package management/building solution to use (e.g. Pip vs Anaconda in Python)
  * How to distribute
    * Use mechanisms supported by language tooling - make it easy for your end users
    * Publish in public artefact repository: PyPI for Python, CRAN for R, Maven for Java
	* GitHub Package Registry - still in beta
	* Local (private) artefact repository
	  * Nexus or Artifactory
	  * Cache public repositories
	  * Can store private packages in same manner as publicly released packages
	  * Useful during development and for testing release process
	  
* Application distribution - native
  * Distribution artefact is a runnable application
  * Key issues
    * platform/OS specific build and packaging
	* required dependencies
  * How to distribute:
    * download from web site (e.g. GitHub)
	
* Application distribution - containers
  * Distribution artefact is a Docker image. 
  * Other container technologies exist but Docker is the de facto standard
  * Overcomes dependencies and platform/OS issues
  * How to distribute:
    * Publish in public Docker registry (Docker Hub, cloud providers, etc)
    * GitHub Package Registry - still in beta	

* Application distribution - services
  * Distribution artefact is access to an API - distributing functionality rather than code
  * Overcomes all issues with dependencies including hardware
  * How to distribute:
    * You are now responsible for running as well as building the code
	* Examples;
	  * Package as code and deploy as plugin or module of web server (e.g. mod_wsgi for Python on Apache, Java servlet)
	  * Package using Docker and run directly or using container orchestration (e.g. Kubernetes)
	
* Platform as a service (PaaS)
  * Heroku, Google App Engine, etc
  * Serverless frameworks
  * Vendor specific packaging and deployment approaches
    * Some are now using Docker as the distribution artefact
	


\newpage