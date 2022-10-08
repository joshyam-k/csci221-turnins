## 1

(a)

Other files that you can run that do not exist in your current directory will likely be in the parent directory of your current working directory if one exists. You can type `cd ..` in the terminal to change to the parent directory. If you are in the root directory then running that command will not take you anywhere. 

(b)


(c)

You can run `cat file1 file2 > file1_2_combined`


## 2

(a)

done!

(b)

This sort of depends on where you are in the whole process of `git add`, `git commit`, and `git push`.

- If you have changed a file that you didn't want to change but haven't run `git add` then you can use `git checkout <file_name>`

- If you have run `git add` but haven't committed yet then you can run `git reset HEAD <file_name>`. At this point the changes have been unstaged but they still exist so you can then use `git checkout <file_name>`.

- If you have added and committed a file but have not pushed it you can run `git reset HEAD~` followed by `git checkout <file_name>`

- If you have added, committed, and pushed a file then you can run `git revert <commit-hash>` where the commit-hash is one from before the one that you recently pushed.

(c)

When you experience a merge conflict in git you will see the following pattern in the file that experienced the conflict

```
<<<<<<< HEAD 
content from one source
=======
content from another source
>>>>>>> NEW-branch-to-be-merged
```

This indicates the source of the merge conflict and it is often easiest to just choose what content you want to leave and then remove all of the `=`, `<`, and branch names and then add, commit, and push the change. This is a very logical strategy as we essential make a new copy of the file which highlights the merge conflict, we then fix the conflict in that file and push our changes.


## 3

I am going to redo question 3 on the numbers lab. As is my code looks like 

```
int overflow_check(int32_t a, int32t_b){
    int 32_t res = a + b;
    if (a > 0 && b > 0 && res <= 0){
        return 1;
    } else if(a < 0 && b < 0 && res >= 0){ 
        return 2;
    } else {
        return 0;
    }
}

void overflow(int32_t a, int32_t b){
    int64_t check = (int64_t) a + (int64_t) b;
    int64_t res;
    int tfoverflow = overflow_check(a, b);
    if (tfoverflow == 0) {
        res = (int64_t) (a + b);
    } else if(tfoverflow == 1){
        res = ((int64_t) (a + b)) + pow(2, 32); 
    } else {
        res = ((int64_t) (a + b)) - pow(2, 32);
    }
}
```

There are a couple of issues with the code that I had originally written. First and foremost, checking for signed overflow after the addition takes place is undefined in C. In both the `overflow_check()` and `overflow()` function I cause undefined behavior which means that the function simply doesn't work how I want it to work. Secondly, we are supposed to return the output as a 64 bit integer but my `overflow()` function does not return anything. Finally, I create a variable called
check but I do not ever compare my output to that check and so it is simply not being used at all.






