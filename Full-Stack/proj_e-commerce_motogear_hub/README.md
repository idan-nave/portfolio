# E-Commerce Website README

## Project Overview
This project is an e-commerce website built using HTML and CSS. It includes essential components such as a navigation bar, hero section with background video, product listings, individual product pages, and a footer with social media links. The site is designed to be fully responsive and features transitions for a smooth user experience.

project was inspired by https://www.revzilla.com/motorcycle-parts



## Features

### 1. **Home Page**
   - **Navigation Bar**: Contains links to the different sections of the page (Hero, Products, and Footer).
   - **Hero Section**: Features a background video with overlay text introducing the site or highlighting a promotional message.
   - **Products Section**: Displays a grid of products where each product is clickable and leads to a dedicated product page.

### 2. **Product Page**
   - **Product Image**: Displays the main image of the selected product.
   - **Price and Options**: Shows the product price along with available options (e.g., color, size).
   - **Back Button**: A button that allows users to return to the home page from the product page.
   - **Bonus Feature**: Product images change based on hovering over different options (e.g., selecting a color or size option).

### 3. **Footer**
   - Contains links to the company's social media profiles.

### 4. **Responsive Design**
   - The website is designed to be fully responsive, ensuring it looks great on all screen sizes (desktop, tablet, mobile).

### 5. **Transitions**
   - At least four smooth CSS transitions implemented for a better user experience (e.g., hover effects, fade-ins, etc.).

## Technologies Used
- HTML5
- CSS3

## Installation Instructions

1. **Clone the Repository**:
   To clone the project to your local machine, run the following command in your terminal:

   ```bash
   git clone https://github.com/your-username/e-commerce-website.git
   ```

2. **Navigate to the Project Directory**:
   After cloning, go into the project directory:

   ```bash
   cd e-commerce-website
   ```

3. **Open in a Browser**:
   You can simply open the `index.html` file in your browser to view the website.

## File Structure
```
/e-commerce-website
    /assets
        /images
            product1.jpg
            product2.jpg
            ...
    /css
        styles.css
    index.html
    product1.html
    product2.html
    ...
```

- `/assets/images`: Contains product images and other media used on the website.
- `/css/styles.css`: The main CSS file that styles the website.
- `index.html`: The home page of the e-commerce website.
- `product1.html`, `product2.html`, ...: Separate HTML files for each product page.

## Transitions Implemented
- Hover effect on product images for a slight zoom-in transition.
- Fade-in effect for the Hero section text.
- Smooth scroll transition for navigation links.
- Hover effect on navigation bar links (color change).

## Deployment

### 1. **GitHub**:
   - Push your local changes to GitHub by following these steps:
     1. Initialize a Git repository if not done already:
        ```bash
        git init
        ```
     2. Add your files:
        ```bash
        git add .
        ```
     3. Commit your changes:
        ```bash
        git commit -m "Initial commit"
        ```
     4. Push to GitHub:
        ```bash
        git remote add origin https://github.com/your-username/e-commerce-website.git
        git push -u origin master
        ```

### 2. **Netlify**:
   - After pushing your code to GitHub, link your repository to Netlify by following the steps on the Netlify dashboard to deploy your website.
   - Once deployed, Netlify will provide you with a live URL to access your website.

## Contributing
Feel free to fork this repository and submit pull requests with improvements or fixes. Contributions are welcome!

## License
This project is licensed under the MIT License.

---

Enjoy browsing the e-commerce site!
