# Git Basics

## What is SCM and why Git is different
### Software Configuration Management
- Track changes to code
- Facilitate collaboration working on the same code base
- Identifying causes of defects
- Facilitate build & release process including continuous integration, continuous delivery.

### GIT
- Decentralised
- Light weight branching
- No "Trunk"/Special branches - All branches are equal


## Getting Started
### Some terms we will be using
- Working Tree
- Index
- Staging
- Head
### Demonstration 00.1
Taking a directory on the file system initialise as a GIT repo and commit files

 - Initialise a repo (run at the root of the project)
 > `git init`
 - Stage files - Current state of selected files are stage for the next commit
 > `git add <files>`
 - Commit - Commits changes to the repository
 ```
 git commit
 git commit -m "My commit message"
 ```
 - Viewing the status of the working tree
```
git status
```
 

*Note on staging*: Once a file is stage and further changes made before the commit will not be committed unless those changes are also staged.

### Exercise 00.1
Take your existing code initialise, stage and commit 

## Log and Diff
### Demonstration 00.2
Makes changes in the working directory and view differences from HEAD

- View all differences
> `git diff`

- View diffences for specific files
> `git diff <files>`

Commit some more changes a view the log
- View the log
> `git log`

View difference between HEAD and a previous commit
> `git diff <commit> HEAD`

View difference between working directory and a previous commit
> `git diff <commit>`

View difference between two commits
> `git diff <commit> <commit>`

### Exercise 00.2
1. Initialise a new git project to experiment with (we will call this the sandbox project). Try out making changes in working tree and commit changes using the `git diff` command to view the changes.
2. Initialise a new git project for you project code.

### Other index/staging commands
These command update both the Working tree and the index 
- Move/rename a files
> `git mv <files>`  
- Remove files
> `git rm <files>`

## Demonstration 00.2
Working with GIT in PyCharm/CLion
