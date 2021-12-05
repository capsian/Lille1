#!/bin/bash

ServerIP=10.201.0.47
#ServerIP=localhost

. ./test_scripts/enroll_API.sh

. ./test_scripts/channel_API.sh

. ./test_scripts/install_API.sh

. ./test_scripts/instantiate_API.sh


#. ./test_scripts/query_API.sh

. ./test_scripts/add_seats_API.sh