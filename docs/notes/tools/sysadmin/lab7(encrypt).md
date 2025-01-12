# Encrypt

-   Decrypt `file1.txt.gpg` with the password `ocfdecal` (_for real-life purposes, never store passwords in plaintext_). What are the decrypted contents of `file1.txt.gpg`?

    command `gpg -d file1.txt.gpg` 
    quack

-   What command allows you to import a key?

    `gpg --import ` 

-   What command allows you to export a key to a file? (Add the `--armor` flag to ASCII-encode the key so it can be sent easily in text form)

    `gpg --export --armor` 

-   What command allows you to see all of the keys on your keyring?

    `gpg --list-keys` 

-   Use the private key `lab7privkey` to decrypt the file `file2.txt.gpg` (_for real-life purposes, it is necessary to keep private keys secret_). What are the decrypted contents of `b8/file2.txt.gpg`?

        gpg --import lab7privkey 
        gpg -d file2.txt.gpg

Hashing

md5sum file3.txt
ddbefc9c1d8a8d9195a420a7181352e9  file3.txt

md5sum file3.txt | cut -d ' ' -f 1 | sha1sum
15c3d7fa41fcc2ed98c2fda065e3248047a048f4  -

file permission
a: file owner, group, people not in the group
u: file owner 
g: group
o: other people who are not in the group

Make this file executable and execute it.
- chmod u+x file5

change file to be under my permission:  
- chmod code_server file6.txt

Make this file readable only to you. What command did you use?
- chmod u-r file7.txt

Change this file’s permissions such that only root should be able to read this file and no one should be able to edit it. What command did you use?
- chmod a-rwx file8.txt

Choose any method to make this file readable to you and unreadable to the previous owner. What command did you use?
- change the ownership, and chmod o-rwx file9.txt

