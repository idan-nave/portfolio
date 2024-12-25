package com.myapp.service;

import com.myapp.model.User;
import com.myapp.dao.UserDao;
import org.junit.Test;
import static org.junit.Assert.*;

public class UserServiceTest {

    @Test
    public void testAddUser() {
        UserDao userDao = new UserDao();
        UserService userService = new UserService(userDao);

        User user = new User(1, "John Doe");
        userService.addUser(user);

        User result = userService.getUserById(1);
        assertNotNull(result);
        assertEquals("John Doe", result.getName());
    }
}
