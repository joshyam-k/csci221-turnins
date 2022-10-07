## 1

(a)
\\
Other files that you can run that do not exist in your current directory will likely be in the parent directory of your current working directory if one exists. You can type `cd ..` in the terminal to change to the parent directory. If you are in the root directory then running that command will not take you anywhere. 

(b)


(c)
\\
You can run `cat file1 file2 > file1_2_combined`


## 2

(a)
\\
done!

(b)
\\
This sort of depends on where you are in the whole process of `git add`, `git commit`, and `git push`.
\\

If you have changed a file that you didn't want to change but haven't run `git add` then you can use `git checkout <file_name>`

If you have run `git add` but haven't committed yet then you can run `git reset HEAD <file_name>`. At this point the changes have been unstaged but they still exist so you can then use `git checkout <file_name>`.

If you have added and committed a file but have not pushed it you can run `git reset HEAD~` followed by `git checkout <file_name>`

If you have added, committed, and pushed a file then you can run `git revert <commit-hash>` where the commit-hash is one from before the one that you recently pushed.






