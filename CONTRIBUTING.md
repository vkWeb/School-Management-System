# Contributing Guidelines

## Forking and cloning the repository

**Step 1:** Install [Git](https://git-scm.com/).

**Step 2:** Fork the repository. Then clone it to your local machine by typing the below command in `Git Bash`(comes with Git):

```bash
# clone the repository
$ git clone https://github.com/YOUR_USERNAME/school-management-system.git
```

Replace `YOUR_USERNAME` with your GitHub username :stuck_out_tongue_winking_eye:.

## Time to Git

> **Remember:** In the world of Git, your forked copy is referred as `origin` and the original repository from which you forked is referred as `upstream`.

**Step 3:** Setting up the remote.

Let us first change our current directory to the project folder:

```bash
$ cd school-management-system
```

Its time to connect your forked copy(`origin`) to the original repository (`upstream`).

```bash
$ git remote add upstream https://github.com/vkWeb/school-management-system.git
```

To double check if everything is in place, type:

```bash
$ git remote -v
```

The output on your terminal should be something like this:

```bash
origin    https://github.com/YOUR_USERNAME/school-management-system.git (fetch)
origin    https://github.com/YOUR_USERNAME/school-management-system.git (push)
upstream    https://github.com/vkWeb/school-management-system.git (fetch)
upstream    https://github.com/vkWeb/school-management-system.git (push)
```

**Step 4:** Let's sync the forked copy with the original repository.

> **Remember:** Before you start writing code, you should **always create a new branch**. But before you create a new branch, **always sync your master branch with the upstream**. Follow the below commands to sync your master branch with upstream. Do this everytime before you start working on a new issue or feature.

```bash
# switches to master branch
$ git checkout master
# updates your local copy to the latest version
$ git fetch upstream
# your fork is now synced with upstream
$ git reset --hard upstream/master
# push synced master branch to your fork for clean history
$ git push origin master --force
# now, create a new branch. Remember to give it a descriptive name
$ git checkout -b goodBranchName
```

After you have synced your forked copy and created a new branch by following above commands. It makes us ready to move ahead.

## Setting up the development environment

**Step 5:** Install [VSCode](https://code.visualstudio.com/) - a great code editor by Microsoft, we'll be using this in our project. Then install these VSCode extensions: [Prettier](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode) (My favorite code formatter) and [Microsoft C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) (Enables C++ IntelliSense).

VSCode doesn't come with a default C++ compiler. So, first we will need to install a C++ compiler to compile our code. We will use MinGW's GCC.

**Step 6:** Install [MinGW](http://www.mingw.org/). Then make sure you have added `C:\MinGW\bin` to your [system variable path](https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/).

Open the project folder in VSCode as an administrator. You can run your code by typing the below commands in VSCode's integrated terminal (you can open it with the shortcut `` (ctrl + `) ``:

```bash
# compiles the source file and converts object file to executable
$ g++ -g main.cpp -o app
# runs the executable
$ ./app
```

## Pushing code to the GitHub repository and opening a Pull request

When you feel confident with your code, you can push it to GitHub.

**Step 7:** You should often check the status of your local copy, it tells you about the modified files and the branch you are in. You can check status by typing:

```bash
# tells you the status of your local copy and the branch you are in
$ git status
```

The output maybe something like:

```bash
On branch school-data/add-student
Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

      modified:   README.md
```

**Step 8:** Add files for commit and push them to GitHub.

```bash
# adds the files you want to commit, often it will be main.cpp only
$ git add main.cpp
# commits the files
$ git commit -m "Put here a descriptive message of the changes you made"
# pushes your code to GitHub
$ git push origin yourBranchName
```

**Step 9:** Open https://github.com/YOUR_USERNAME/school-management-system.git in your browser and click on `Compare & pull request` to create a new pull request.

![recently pushed branch](assets/recently_pushed_branch.png)

Now, describe the changes you made then click on `Create pull request` and wait for your glory :tada:!

![pull request send](assets/pr-send.png)

If you need any help in setting up the project or if you are stuck somewhere then you can [open an issue](https://github.com/vkWeb/school-management-system/issues/new). I will try my best to resolve it.

### You are a champion. Happy Coding :)
