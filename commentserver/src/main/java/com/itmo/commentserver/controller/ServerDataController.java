package com.itmo.commentserver.controller;

import com.itmo.commentserver.entity.Comment;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.BindingResult;
import org.springframework.validation.FieldError;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.CopyOnWriteArrayList;

@RestController
@RequestMapping("/")
@RequiredArgsConstructor(onConstructor = @__(@Autowired))
public class ServerDataController {
    private final CopyOnWriteArrayList<Comment> commentList;

    @GetMapping("/")
    @ResponseBody
    public List<Comment> initGet(){
        return commentList;
    }

    @PostMapping("/add")
    public String addData(@RequestBody
                            @Valid Comment comment,
                        BindingResult bindingResult){
        if (bindingResult.hasErrors()){
            List<FieldError> fieldErrors = bindingResult.getFieldErrors();
            FieldError fieldError = bindingResult.getFieldError();
            String message = fieldError.getDefaultMessage();
            return message;
        }
        commentList.add(comment);
        System.out.println(comment);
        return "success";
    }


}
