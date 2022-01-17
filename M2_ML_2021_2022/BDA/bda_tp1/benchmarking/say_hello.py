import api_microblog as api
import utils
import time

# This script write a hello message from each user to each user

# get users (stored by password)
users = utils.get_users()

mb = api.microblog(utils.db_ip)

# loop
for u_password_1 in users:
    u_first_name_1 = users[u_password_1]['first_name']
    u_last_name_1 = users[u_password_1]['last_name']

    # scnd loop
    for u_password_2 in users:
        if u_password_2 != u_password_1:
            u_first_name_2 = users[u_password_2]['first_name']
            u_last_name_2 = users[u_password_2]['last_name']

            msg = 'Hello ' + u_first_name_2 + " " + u_last_name_2 + ", I'm " + u_first_name_1 + " " + u_last_name_1

            ret = mb.publish_post(u_first_name_1 + ' ' + u_last_name_1, u_password_1, msg)
            print(msg, "acc_time:", mb.acc_time, "nb_query:", mb.nb_query, "ret:", ret)
