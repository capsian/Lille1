# Rendu "Les droits d’accès dans les systèmes UNIX"

## Author

- ABDULLAH Mohamad <mohamad.abdullah.etu@univ-lille.fr>
- LAKHDAR Selim <selim.lakhdar.etu@univ-lille.fr>

## Question 1

```
ubuntu@isi:~$ sudo adduser toto
ubuntu@isi:~$ sudo usermod -aG ubuntu toto
```
- On ne peut pas écrire : Permission denied
- La raison est parce que les droits user ne le permettent pas. On ne peut que lire le fichier.

## Question 2

```
ubuntu@isi:/home/ubuntu/isi-tp1$ mkdir mydir && chmod g-x mydir
toto@isi:/home/ubuntu/isi-tp1$ cd mydir/
bash: cd: mydir/: Permission denied
ubuntu@isi:~/isi-tp1$ echo "hello" > mydir/data.txt
toto@isi:/home/ubuntu/isi-tp1$ ls -al mydir/
ls: cannot access 'mydir/.': Permission denied
ls: cannot access 'mydir/..': Permission denied
ls: cannot access 'mydir/data.txt': Permission denied
total 0
d????????? ? ? ? ?            ? .
d????????? ? ? ? ?            ? ..
-????????? ? ? ? ?            ? data.txt
```

- Le caractère x pour un répertoire signifie que l'on peut y accéder.
- On ne peut pas accéder à mydir avec l'utilisateur toto car il appartient au groupe ubuntu qui n'a pas le droit d'exec.
- One ne peut pas lister avec le user toto

## Question 3

```
ubuntu@isi:~/isi-tp1/question3$ ll
total 16
drwxrwxr-x 2 ubuntu ubuntu 4096 Mar  2 10:56 ./
drwxrwxr-x 5 ubuntu ubuntu 4096 Mar  2 10:43 ../
-rw-rw-r-- 1 ubuntu ubuntu   84 Mar  2 10:56 Makefile
-rw-rw-r-- 1 ubuntu ubuntu  504 Mar  2 10:54 suid.c
toto@isi:/home/ubuntu/isi-tp1/question3$ ./suid 
EUID: 1001
EGID: 1001
RUID: 1001
RGID: 1001

Cannot open file
```

- On n'arrive pas à ouvrir le fichier. 

```
toto@isi:/home/ubuntu/isi-tp1/question3$ su ubuntu
ubuntu@isi:~/isi-tp1/question3$ chmod u+s suid
ubuntu@isi:~/isi-tp1/question3$ su toto
toto@isi:/home/ubuntu/isi-tp1/question3$ ./suid 
EUID: 1000
EGID: 1001
RUID: 1001
RGID: 1001

hello
```

- On arrive à ouvrir le fichier avec le flag set-user-id.
- On remarque que le EUID vaut 1000 (celui du user ubuntu)

## Question 4

```
ubuntu@isi:~/isi-tp1/question4$ ll
total 12
drwxrwxr-x 2 ubuntu ubuntu 4096 Jan 20 15:29 ./
drwxrwxr-x 5 ubuntu ubuntu 4096 Mar  2 10:43 ../
-rwSrw-r-- 1 ubuntu ubuntu   15 Jan 20 15:29 suid.py
toto@isi:/home/ubuntu/isi-tp1/question4$ python3 suid.py 
EUID: 1001
EGID: 1001
```

- Pour changer de password, la commande passwd est utilisée.
- Elle se lance avec le droit root puis drop ses privilèges.

## Question 5

- le fichier /etc/passwd est un fichier texte qui liste les différents users du system.

- La commande chfn permet de modifier le nom complet et les informations associées à un utilisateur.

```
toto@isi:/home/ubuntu/isi-tp1/question4$ ls -al /usr/bin/chfn 
-rwsr-xr-x 1 root root 85064 May 28  2020 /usr/bin/chfn
```

- On remarque que chfn possède le setuid flag. Qu'il appartient au user root, group root.
- Il est exécutable par tout le monde.

```
toto@isi:/home/ubuntu/isi-tp1$ cat /etc/passwd
.....
toto:x:1001:1001:,,,:/home/toto:/bin/bash
toto@isi:/home/ubuntu/isi-tp1$ chfn
Password: 
Changing the user information for toto
Enter the new value, or press ENTER for the default
	Full Name: 
	Room Number []: 1
	Work Phone []: 123456
	Home Phone []: 12345
toto@isi:/home/ubuntu/isi-tp1$ cat /etc/passwd
.....
toto:x:1001:1001:,1,123456,12345:/home/toto:/bin/bash
```

## Question 6

- Les mots de passe sont stockés dans le fichier /etc/shadow et ne sont accessible que par le root.
- Les mots de passes sont chiffrés.

```
# https://www.computernetworkingnotes.com/rhce-study-guide/etc-shadow-file-in-linux-explained-with-examples.html
Historically, the /etc/passwd file used to store all login information in a standalone Linux system. Later, due to following reasons password information was moved in /etc/shadow file.

    The /etc/passwd file has only one field for password information. Since there is only one field, besides encrypted password other password related information cannot be stored in this file.
    For password encryption, the /etc/passwd file supports basic algorithm such as DES. A hacker can easily reveal a password encrypted with DES algorithm.
    The /etc/passwd file is world readable. It means any local user can view the passwords stored in this file.

The /etc/shadow file addresses all above issues.

    The /etc/shadow file has nine fields to store encrypted password and other password related information.
    The /etc/shadow file supports all advanced algorithms and has plenty of room for further updates.
    The /etc/shadow file is readable only by root user.

```

## Question 7

````
cd question7
./clean.sh
./init.sh
./test_admin.sh
./test_lambda_a.sh
./test_lambda_b.sh
````

## Question 8

````
cd question8
./clean.sh
./init.sh
./test.sh
````
````
lambda_a tests
 lambda_a trying to delete dir_b/lambda_b.txt
Wrong GID, Permission denied dir_b/lambda_b.txt
 lambda_a trying to delete dir_a/lambda_a.txt (wrong password)
Enter your password: incorrect password !
 lambda_a trying to delete dir_a/lambda_a.txt (correct password)
Enter your password: dir_a/lambda_a.txt removed !
lambda_b tests
 lambda_b trying to delete dir_a/lambda_a.txt
Wrong GID, Permission denied dir_a/lambda_a.txt
 lambda_b trying to delete dir_b/lambda_b.txt (wrong password)
Enter your password: incorrect password !
 lambda_b trying to delete dir_a/lambda_a.txt (correct password)
Enter your password: dir_b/lambda_b.txt removed !
````
```
ubuntu@isi:~/isi-tp1/question8$ ls -al rmg
-rwsrwxr-x 1 admin ubuntu 17448 Mar  2 14:31 rmg
ubuntu@isi:~/isi-tp1/question8$ ls -al /home/admin/passwd 
-rw-rw---- 1 admin admin 42 Mar  2 14:31 /home/admin/passwd
```

## Question 9

````
cd question9
./clean.sh
./init.sh
./test.sh
````
```
ubuntu@isi:~/isi-tp1/question9$ ./test.sh 
lambda_a tests
 lambda_a trying to set passwd for first time
Enter new password: 
=> new password: lambda_a

 lambda_a trying to change passwd with wrong old one
Enter old password: 
=>old password: lambda_b
Not matching !
 lambda_a trying to change passwd with right old one
Enter old password: 
=>old password: lambda_a
Enter new password: 
=> new password: hello

```

## Question 10

````
cd question10
./clean.sh
./init.sh
sudo ./groupe_server # dans un terminale
sudo -u lambda_a bash -c './groupe_client cmds.txt' # dans un autre terminale
````








