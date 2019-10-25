# Remotes and GitHub

## Git Remotes
- A remote a is repository on a server that is tracked by the local repository
- Git is decentralised and can have multiple remote servers
- Local branches can be configured track remote branches
- Different branches can track different remotes

Adding a remote:
```
git remote add <remote name> <remote url>
```
Default remote name is `origin`

Push a branch to a remote branch 
```
git push --set-upstream <remote> <upstream branch name>
```

pushing changes from local branch to remote branch
```
git push
```

pull changes from remote branch to local tracking branch
```
git pull
```

To make you local branch be aware of latest set of remote branches you will need to fetch from the remote

fetching branches and tags from remote
```
git fetch <remote name>
```
If fetching from remote called `orgin`
```
git fetch
```


## GitHub
- GitHub is a hosted Git Server at https://github.com
- Free account allow unlimited public and private projects.  Though only 3 collaborates are permitted on private projects is restricted

### Exercise 02.01
1. Register a at github.com
2. Create a public repository for your project with BSE3 licence 
3. Configure the remote and push master
4. Create a private repository for your sandbox
5. Configure the remote and push all branches
 
*Note:* You will be creating your repository with BSE3 licence.

## Cloning a existing Repository
```
git clone <url>
```

### Exercise 02.02
Create and new project in GitHub and clone it locally
