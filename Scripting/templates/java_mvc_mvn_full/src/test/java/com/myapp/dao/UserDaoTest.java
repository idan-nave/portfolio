package com.myapp.dao;

import com.myapp.model.User;
import org.junit.Test;
import static org.junit.Assert.*;

public class UserDaoTest {

    @Test
    public void testSaveAndFindById() {
        UserDao userDao = new UserDao();

        User user = new User(1, "Jane Doe");
        userDao.save(user);

        User result = userDao.findById(1);
        assertNotNull(result);
        assertEquals("Jane Doe", result.getName());
    }
}
