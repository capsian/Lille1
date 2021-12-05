FROM nginx

# copy content
COPY ./src /usr/share/nginx/html
COPY docker-entrypoint.sh /docker-entrypoint.sh
CMD chmod +x /docker-entrypoint.sh

ENTRYPOINT ["sh", "/docker-entrypoint.sh"]
