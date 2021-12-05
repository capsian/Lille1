package condenses_lex;
/**
 *  YYtoken implementation for ENTIER
 */
public class Entier extends BaseToken{
    private final int value;
    public String getValue(){
        return String.valueOf(value);
    }
    public Entier(int value){
        super(TokenType.ENTIER);
        this.value = value;
    }
    public String toString(){
        return super.toString()+"["+value+"]";
    }

}