users_file = './scripts/users'
db_ip = "172.28.100.140"


def get_users():
    # index by pwd (try to catch collision :D ...)
    dict = {}

    with open(users_file) as f:
        lines = f.readlines()
        for line in lines:
            l = line.split(" ")
            first_name = l[0]
            last_name = l[1].split("\t")[0]
            password = l[1].split("\t")[1].strip()
            # print('first_name:', first_name, 'last_name:', last_name, 'password:', password)
            if password not in dict:
                dict[password] = {
                    'first_name': first_name,
                    'last_name': last_name
                }
            else:
                print('collision with', password, first_name, last_name)
                exit(1)

    return dict

# TEST
# users = get_users()
# print(users)
