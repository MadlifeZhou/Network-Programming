package com.itmo.commentserver;

import com.itmo.commentserver.entity.Comment;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArrayList;

@SpringBootTest
class CommentserverApplicationTests {
    @Autowired
    CopyOnWriteArrayList<Comment> commentList;

    @Test
    public void testMap(){
        String alice = "alice";
        Map<String, String> map = Map.of("username", "zhou", "test", alice);
        HashMap map1 = new HashMap(map);
        map1.put("asdfads","asdfas");
        System.out.println(map1);
    }


}
