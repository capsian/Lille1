CREATE EXTENSION IF NOT EXISTS "uuid-ossp"; -- define uuid_generate_v1 function
CREATE EXTENSION pgcrypto;
-- extension defining functions for storing password securely

--- Database ---
-- CREATE DATABASE article;

--- Articles ---
CREATE TABLE articles
(
    article_id  uuid      DEFAULT uuid_generate_v1() PRIMARY KEY,
    content TEXT,
    published_date TIMESTAMP DEFAULT now()::timestamp
);

CREATE INDEX idx_pub_date ON articles (published_date);
CLUSTER articles USING idx_pub_date;

CREATE FUNCTION get_article(uuid)
	RETURNS table (article_id uuid, content TEXT, published_date TIMESTAMP)  AS
	$$
	SELECT * FROM articles
		WHERE articles.article_id = $1;
	$$ LANGUAGE SQL
	SECURITY DEFINER;

CREATE OR REPLACE FUNCTION get_all()
	RETURNS table (article_id uuid, content TEXT, published_date TIMESTAMP)  AS
	$$
	SELECT * FROM articles
	ORDER BY articles.published_date DESC
    $$ LANGUAGE SQL
	SECURITY DEFINER;

CREATE OR REPLACE FUNCTION insert_article(TEXT)
	RETURNS uuid AS
	$$
	INSERT INTO articles (content) VALUES ($1) RETURNING article_id;
	$$ LANGUAGE SQL
	SECURITY DEFINER;

CREATE FUNCTION update_article(uuid,TEXT)
	RETURNS void AS
	$$
	UPDATE  articles
    SET content = $2
    WHERE article_id = $1
	$$ LANGUAGE SQL
	SECURITY DEFINER;


--- Tags ---
CREATE TABLE Tags
(
    article_id  uuid PRIMARY KEY references articles(article_id),
    tags TEXT[]
);
CREATE INDEX idx_tags ON Tags(tags);
CLUSTER Tags USING idx_tags;

CREATE OR REPLACE FUNCTION insert_tag(uuid, TEXT[])
	RETURNS uuid AS
	$$
	INSERT INTO Tags (article_id, tags) VALUES ($1,$2) RETURNING $1;
	$$ LANGUAGE SQL
	SECURITY DEFINER;

-----
GRANT EXECUTE ON FUNCTION get_article TO postgres;
GRANT EXECUTE ON FUNCTION get_all TO postgres;
GRANT EXECUTE ON FUNCTION insert_article TO postgres;
GRANT EXECUTE ON FUNCTION update_article TO postgres;