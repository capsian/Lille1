CREATE EXTENSION IF NOT EXISTS "uuid-ossp"; -- define uuid_generate_v1 function
CREATE EXTENSION pgcrypto;
-- extension defining functions for storing password securely


--- USER MANAGEMENT ---
CREATE TABLE user_store
(
    user_id  uuid DEFAULT uuid_generate_v1() PRIMARY KEY,
    name     TEXT UNIQUE,
    password TEXT
);
CREATE INDEX idx_name ON user_store (name);
CREATE FUNCTION create_user(TEXT, TEXT)
    RETURNS uuid AS
$$
INSERT INTO user_store(name, password)
VALUES ($1, crypt($2, gen_salt('bf')))
RETURNING user_id;
$$ LANGUAGE SQL
    SECURITY DEFINER;

--- MESSAGE MANAGEMENT ---

CREATE TABLE messages_store
(
    message_id     uuid      DEFAULT uuid_generate_v1() PRIMARY KEY,
    content        TEXT,
    published_date TIMESTAMP DEFAULT now()::timestamp,
    replies_to     uuid      DEFAULT NULL,
    user_id        uuid REFERENCES user_store (user_id) NOT NULL
);

CREATE INDEX idx_pub_date ON messages_store (published_date);
CLUSTER messages_store USING idx_pub_date;

CREATE FUNCTION insert_message(TEXT, TEXT, TEXT, uuid) --- (name, password, content, replies_to)
    RETURNS uuid AS
$$
INSERT INTO messages_store(content, user_id, replies_to)
SELECT $3, user_store.user_id, $4
FROM user_store
WHERE name = $1
  and password = crypt($2, password)
RETURNING message_id;
$$ LANGUAGE SQL
    SECURITY DEFINER;

CREATE VIEW messages AS
SELECT message_id, content, published_date, replies_to, name, messages_store.user_id
FROM messages_store
         INNER JOIN user_store ON messages_store.user_id = user_store.user_id
ORDER BY published_date DESC
LIMIT 30;

--- Followers (one to many relation) ---

CREATE TABLE followers
(
    user_source uuid REFERENCES user_store (user_id) NOT NULL,
    user_target uuid REFERENCES user_store (user_id) NOT NULL,
    CONSTRAINT uniq_cstr UNIQUE (user_source, user_target),
    CONSTRAINT not_self_follow CHECK (user_source != user_target)
);

CREATE INDEX idx_follower ON followers (user_source, user_target);

CREATE FUNCTION feed(TEXT, TEXT) --- Produce the feed of some user args: (name, password)
    RETURNS table
            (
                message_id     uuid,
                content        TEXT,
                published_date TIMESTAMP,
                replies_to     uuid,
                user_name      TEXT
            )
AS
$$
SELECT message_id, content, published_date, replies_to, store2.name
FROM user_store as store1
         INNER JOIN followers ON store1.user_id = followers.user_source
         INNER JOIN messages_store ON followers.user_target = messages_store.user_id
         INNER JOIN user_store as store2 ON followers.user_target = store2.user_id
WHERE store1.password = crypt($2, store1.password)
  and $1 = store1.name
ORDER BY published_date DESC;
$$ LANGUAGE SQL
    SECURITY DEFINER;

CREATE FUNCTION follow(TEXT, TEXT, uuid) -- name, password, uuid to follow
    RETURNS void AS
$$
INSERT INTO followers
SELECT user_id, $3
FROM user_store
WHERE password = crypt($2, password)
  and $1 = name
ON CONFLICT DO NOTHING;
$$ LANGUAGE SQL
    SECURITY DEFINER;

--- COMMON ROLE ACCESS (main user API) ---

DROP ROLE IF EXISTS common_user;
CREATE ROLE common_user LOGIN;
GRANT EXECUTE ON FUNCTION create_user TO common_user;
GRANT EXECUTE ON FUNCTION insert_message TO common_user;
GRANT EXECUTE ON FUNCTION follow TO common_user;
GRANT EXECUTE ON FUNCTION feed TO common_user;
GRANT SELECT ON messages to common_user;

-----

CREATE OR REPLACE FUNCTION get_user_messages(TEXT) RETURNS json AS -- username
$BODY$
DECLARE
    found_uuid TEXT;
BEGIN
    -- retrieve uuid
    SELECT user_id INTO found_uuid FROM user_store WHERE name = $1;
    -- Build the JSON Response:
    RETURN (
        SELECT json_build_object(
                       'user_id', (found_uuid),
                       'messages', (SELECT json_agg(content) FROM messages_store WHERE user_id = uuid(found_uuid) LIMIT 10)
                   )
    );
END
$BODY$
LANGUAGE 'plpgsql';