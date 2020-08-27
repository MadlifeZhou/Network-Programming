package com.itmo.commentserver.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.hibernate.validator.constraints.Length;

import java.io.Serializable;

@Data
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Comment implements Serializable {
    private static final long serialVersionUID = 7122573081058753307L;
    @Length(min = 1,max = 10,message = "Username is too long")
    private String username;
    @Length(min = 1,max = 100,message = "Comment is too long")
    private String comment;
}
