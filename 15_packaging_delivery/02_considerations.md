
# Considerations

## Modes of delivery

* TODO: outline the various different ways of packaging and delivering software

## Secondary artefacts

* TODO: artefacts other than primary - source code, documentation, clients for services, etc. ...

## Versioning

* Assign unique version names or numbers to released (or pre-released) software
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