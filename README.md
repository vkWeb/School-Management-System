# school-management-system

We are going to build an advanced school management system with C++ for our school project.

> The project is in very **early stage of development**. To see the tasks undergoing, you can visit the [Project board](https://github.com/vkWeb/school-management-system/projects/1)

> **Note:** This project will be developed in a shared repository model. So, if you wish to contribute to this project you can email at vivekmittalagrawal@gmail.com

## Installation Process

### Cloning the repository

**Step 1:** Install [Git](https://git-scm.com/).

**Step 2:** Clone this repository to your local machine by typing the below command in Git bash:

```bash
#This command will clone this git repo
$ git clone https://github.com/vkWeb/school-management-system.git
```

### Installing the code editor and required extensions

**Step 3:** Install [VSCode](https://code.visualstudio.com/) - a great code editor by Microsoft, We'll be using this in our project then Install these VSCode extensions: [Prettier](https://marketplace.visualstudio.com/items?itemName=esbenp.prettier-vscode) and [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

### Creating a new branch and running the code

Before you start writing code, you should always create a new branch to maintain the proper working workflow.

**Step 4:** **Always remember to update your local copy before creating a new branch!** You can do it by typing:

```bash
#Switches to master branch
$ git checkout master
#Updates your local copy to the latest version
$ git pull origin master
#Creates a new branch, remember to give it a descriptive name
$ git checkout -b yourBranchName
```

A compiler is a must to compile code. So lets set-up a compiler before writing any code.

**Step 5:** Install [MinGW](http://www.mingw.org/) - our compiler and make sure you have added `C:\MinGW\bin` to your system variable path.

Open your cloned folder in VSCode as an administrator. You can run your code by typing the below commands in VSCode's integrated terminal (you can open it by typing `` (ctrl + `) ``:

```bash
#Compiles the source file and converts object file to executable
$ g++ main.cpp -o app
#Runs the executable
$ ./app
```

### Pushing code to the GitHub repository and opening a Pull request

When you feel confident with your code, you can push it to GitHub (often referred as remote).

**Step 6:** You should often check the status of your local copy, it tells you about the modified files and the branch you are in. You can check status by typing:

```bash
#Tells you the status of your local copy and the branch you are in
$ git status
```

Now, lets add files for commit and push them to GitHub.

```bash
#Adds the files you want to commit, often they will be main.cpp and app.exe
$ git add main.cpp app.exe
#Commits the files
$ git commit -m "Put here a descriptive message of the changes you made"
#Pushes your code to GitHub
$ git push origin yourBranchName
```

**Step 7:** Open https://github.com/vkWeb/school-management-system in your browser and click on `Compare and Pull Request` to create a new pull request. Describe the changes you made and wait for your glory :tada:!

**You are the best. Happy Coding :)**
