package com.myapp.dao;

import com.myapp.model.Product;
import java.util.HashMap;
import java.util.Map;

public class ProductDao {

    private Map<Integer, Product> database = new HashMap<>();

    public Product findById(int id) {
        return database.get(id);
    }

    public void save(Product product) {
        database.put(product.getId(), product);
    }
}
