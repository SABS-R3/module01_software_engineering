
# CI/CD: Continuous Integration/Continuous Delivery (or Deployment)

## Automation of software building, packaging, delivery, and deployment.

* Continuous integration
  * Code is checked out of Git repository, built, and tested automatically with every commit
  * Commit to shared repository often (multiple times a day)
  * Aim is to highlight errors quickly, especially around integration of multiple development strands
  * Addresses the "works on my machine" issue
* Continuous delivery
  * Logical extension of CI to include the automation of the delivery process
  * Goal: one branch of project is always ready to be released
  * Adds automated building and packaging of release artefacts
  * Add more automated tests, possibly using the release artefacts
  * Actual release or deployment of release is manual
* Continuous deployment
  * Automated release/deployment process: if continuous delivery pipeline is successful then release/deploy
  * What tests, or other processes, are needed to trigger a release; automate all of these
* Automate everything
  * Reality (small teams): automate what's reasonable
  * Continuous deployment as aspirational goal
  * Toolsets are rapidly improving - what's reasonable (for a small team) is getting better

\newpage