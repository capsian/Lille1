HOST="http://127.0.0.1:5000"
HEADER="Content-Type: application/json"
DATA='{"review_content":"Excellent produit je recommande fortement !", "review_title":"Bon produit au soleil", "review_stars":"2"}'




curl -H $HEADER -X POST --data "$DATA" $HOST/predict
#curl -H $HEADER -X POST --data '{"username":"xyz","password":"xyz"}' http://127.0.0.1:5000/predict
