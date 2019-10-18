
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
	  * Package as code and deploy as plugin or module of web server (e.g. mod_wsgi for Python on Apache)
	  * Package using Docker and run directly or using container orchestration such as Kubernetes
	
* Platform as a service (PaaS)
  * Heroku, Google App Engine, etc
  * Serverless frameworks
  * Vendor specific packaging and deployment approaches
    * Some are now using Docker as the distribution artefact
	

## Secondary artefacts

additional artefacts produced on release that can be useful for the end user

* Documentation
  * Follow conventions from language or community - this will be what the user expects (as minimum)
  * What type of documentation is useful?
    * API documentation 
	* Textual description or manual
  * How to distribute?
    * README and Wiki in GitHub repository - documentation is close to code
	* Separate web page (possibly tied to Git repo - e.g. GitHub pages)
    * downloadable PDF
	* packaged for IDE use
* Source code
  * downloadable zipped file - is this needed as code is accessible via GitHub?
  * packaged for IDE use
* Service client code
  * You or user responsible for writing client code?
  * Which language(s)?
  * Client code generation tooling taking over 

## Versioning

how to assign unique version numbers to released software

* Why versions: user point of view
  * Users can use specific versions of software
  * Multiple versions allow users to upgrade when *they* are ready
* Why versions: developer point of view
  * Developers know which version they are working on
  * Bug reports are filed against specific versions
  * Feature releases can be planned for specific versions
* Semantic versioning[^semantic_versioning]
  * Has meaning (version number has semantics)
  * Format: MAJOR.MINOR.PATCH (e.g. 2.5.8)
    * All increment with new release
    * PATCH: backward compatible bug fixes are introduced. Reset to zero with MINOR or MAJOR release.
	* MINOR: backward compatible functionality is introduced to the public API. May indicate substantial new functionality in private code. Reset to zero with MAJOR release.
	* MAJOR: backward incompatible changes are introduced to the public API. 
  * 1.0.0 as first non-beta release
  * Responsibility of developers to ensure semantics are as expected
    * Can be subjective, e.g. what is "substantial new functionality"
* Other approaches
  * Used by systems that need unique version ID
  * More suitable than semantic versioning for automated release and deployment approaches
  * No semantics
  * Generally used for internal version numbers (i.e. not released to end users)
  * Examples;
    * Git commit hash (e.g. 1ecfd275763eff1d6b4844ea3168962458c9f27a) 
    * CI/CD run number (auto incrementing integer)
    * Build timestamp  

## API design[^api_design]

* API: Application programming interface
* API is the public face of your software.
  * People will use software with a good API and avoid software with a bad API
* Separate API from implementation
  * Solid API allows implementation to change with minimal effect on end users
* Public APIs are forever - one chance to get it right.
  * Versioning can mitigate this somewhat but with an increased maintenance burden

## Licenses

* Default open source license for projects is BSD 3
* Possible talk by open source license expert later in year

[^semantic_versioning]: [Semantic versioning](https://semver.org/)
[^api_design]: [How to Design a Good API and Why it Matters](http://fwdinnovations.net/whitepaper/APIDesign.pdf)


\newpage