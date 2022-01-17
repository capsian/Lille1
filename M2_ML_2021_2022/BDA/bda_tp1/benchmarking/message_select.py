import api_microblog as api
import utils
import time

# get users
users = utils.get_users()

# api
mb = api.microblog(utils.db_ip)

# loop
for u_password_1 in users:
    u_first_name_1 = users[u_password_1]['first_name']
    u_last_name_1 = users[u_password_1]['last_name']

    api.logged(mb.get_feed(u_first_name_1 + ' ' + u_last_name_1, u_password_1))
    print(u_first_name_1 + ' ' + u_last_name_1, "acc_time:", mb.acc_time, "nb_query:", mb.nb_query)



