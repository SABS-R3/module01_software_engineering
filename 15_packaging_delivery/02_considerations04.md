
# Considerations

*what* needs to be considered when planning how to release your software

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