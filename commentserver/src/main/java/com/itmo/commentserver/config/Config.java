package com.itmo.commentserver.config;

import com.itmo.commentserver.entity.Comment;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

import java.util.concurrent.CopyOnWriteArrayList;

@Configuration
public class Config {
    @Bean("CopyOnWriteArrayList")
    public CopyOnWriteArrayList copyOnWriteArrayList(){
        CopyOnWriteArrayList<Comment> comments = new CopyOnWriteArrayList<>();
        comments.add(new Comment("zhou1","I like ITMO"));
        comments.add(new Comment("zhou2","I like HDU"));
        return comments;
    }
}
