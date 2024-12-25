package com.myapp.service;

import com.myapp.model.User;
import com.myapp.dao.UserDao;

public class UserService {

    private UserDao userDao;

    public UserService(UserDao userDao) {
        this.userDao = userDao;
    }

    public User getUserById(int id) {
        return userDao.findById(id);
    }

    public void addUser(User user) {
        userDao.save(user);
    }
}
