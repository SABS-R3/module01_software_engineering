# Branching and Merging

## Working with branches in Git
- Git has no special branches. No trunk (though it does have a default branch "master")
- Git branching is lightweight mean developers can create, merge and discard branches freely
- Can branch from any branch
- Can merge to any branch

Create a branch as a copy of the current branch
```
git branch <branch name>
```

Switch branch
```
git checkout <branch name>
```

Create a branch and switch to that branch
```
git checkout -b <branch name>
```

Comparing current branch to another
```
git diff <other branch>
```

Comparing two other branches
```
git diff <branch one> <branch two>
```

This can also be done in PyCharm and CLion.

## Merging and rebasing

Merging combined the history for the source branch with that of the target.

To merge a branch to the current working branch:
```
git merge <source branch>
```

Rebasing applies the changes from the branch after the changes from another 

To rebase:  
```
git rebase <other branch>
```

### Exercise  01.01
In your sandbox project experiment with branch and rebasing: 
1. Create some branches
2. Commit different new files to each to the branches 
3. Use both merging and rebasing
4. Observer how the git log looks after these changes

## Conflicts
The merge command shown earlier will fail if there are changes to the same files in both branches.
No fast forward merge and resolve conflicts
```
git merge --no-ff <source branch>
```
Resolve the conflicts and use `git add` to mark as merged.  Committing will apply the merge.

Rebasing your source branch may also solve or reduce the merge conflicts

### Exercise 01.02
In pairs take a sandbox project and make changes to the same files  

## Branching Strategy
There are many complex branching strategies (see Git Flow for example). However, it is best to keep it simple.

"Trunk" Development: Keep the latest on master

## Feature branching
- Branch to develop a feature
- Keep features small
- Merge back to master as soon it is ready

![alt text](feature_branching.svg "The feature branching strategy")

## Release Branching
- Required only if multiple versions are to be maintain e.g 2.3.n and 3.0.n

