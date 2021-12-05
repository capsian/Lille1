data Client = Client {	
						nom :: String,
						prenom :: String,
						mail :: String
					} deriving Show

c1 = Client "a" "a" "a"
c2 = Client "b" "b" "b"
c3 = Client "c" "c" "c"

nomPrenom (Client {nom = n, prenom = p}) = n ++ " " ++ p
nomPrenom' c = nom c ++ " " ++ prenom c