package com.myapp.dao;

import com.myapp.model.User;
import java.util.HashMap;
import java.util.Map;

public class UserDao {

    private Map<Integer, User> database = new HashMap<>();

    public User findById(int id) {
        return database.get(id);
    }

    public void save(User user) {
        database.put(user.getId(), user);
    }
}
