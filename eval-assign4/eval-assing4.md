## 1 (Shell)

(a)

I would accomplish this by using the absolute path name inside of whatever command I am running. For example when running my `.c` files for this class I usually do so in the directory that directly contains that file so I'll do `gcc lab3.c -o lab3comp` but regardless of what working directory I am in I can run that same command using `gcc ~/Desktop/csci221-turnins/lab3/lab3.c -o lab3comp`.


(b)

(c)

You can use `head -50 Logistics.tex | grep -o that | wc -l`. This works because the `-o` prints only the matched parts of a matching line which results in separate lines for each unique occurence of the word "that".

## 2 (Version Control)

(a)

Done!

(b)

(c)

In version control a branch is simply a snapshot (copy) of a repository. Branches are extremely useful when you want to experiement with the code or try things with the code in isolation. In other words you can make changes and try things out without affecting the repository itself. It also provides structure for implementing changes from various people in a more checked way. Before a branch is merged back into the main repository people can review it and make sure that they agree
with/want the changes before they are added. 

You can use local branches in git by doing `git checkout -b branch_name` now you can commit to this branch and make changes to it. When you're ready to merge the branch back into the main branch (repository) you need to first run `git checkout main` to checkout the main branch that you want to merge your created branch back into. From here you run `git merge branch_name` to complete the merge. It can be good practice to delete a branch after it has been merged back into the main branch and you can do this with `git branch -d branch_name`.  
