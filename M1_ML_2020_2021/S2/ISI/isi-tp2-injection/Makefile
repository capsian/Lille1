db:
	docker-compose -f ./deployments/docker-compose.yml up -d db adminer
	
up: db
	sleep 10
	docker-compose -f ./deployments/docker-compose.yml up -d web_vul web_sql_correct web_xss
	
down:
	docker-compose -f ./deployments/docker-compose.yml down
