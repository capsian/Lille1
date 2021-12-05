package hello;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.beans.factory.annotation.Value;


@RestController
public class HelloController {

    @Value("${hello.env}")
    private String env;

    @CrossOrigin
    @RequestMapping("/api/hello")
    public Hello world() {
        return new Hello("world");
    }
    
    @CrossOrigin
    @RequestMapping("/api/environment")
    public Environnement env() {
        return new Environnement(env);
    }

}
