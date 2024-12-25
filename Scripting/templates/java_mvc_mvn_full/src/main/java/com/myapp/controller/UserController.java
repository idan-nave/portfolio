package com.myapp.controller;

import com.myapp.model.User;
import com.myapp.service.UserService;

public class UserController {

    private UserService userService;

    public UserController(UserService userService) {
        this.userService = userService;
    }

    public void createUser(int id, String name) {
        User user = new User(id, name);
        userService.addUser(user);
    }

    public void displayUser(int id) {
        User user = userService.getUserById(id);
        System.out.println(user);
    }
}
