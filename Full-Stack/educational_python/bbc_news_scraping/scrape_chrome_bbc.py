from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.chrome.options import Options

# Specify the path to the ChromeDriver executable
chromedriver_path = '/usr/local/bin'  # Replace with the actual path

# Create ChromeOptions instance
chrome_options = Options()

# Add the argument to run Chrome in headless mode
chrome_options.add_argument('--headless')

try:
    # Create a Chrome WebDriver instance with the specified ChromeDriver path and options
    driver = webdriver.Chrome(options=chrome_options)

    # Navigate to the BBC News website
    driver.get('https://www.bbc.com/news')

    # Wait for the page to load (you might need to adjust the sleep time)
    driver.implicitly_wait(10)

    # Print the title of the page
    print("Page Title:", driver.title)

except Exception as e:
    print(f"Exception: {e}")

finally:
    if 'driver' in locals():
        # Close the browser when done
        driver.quit()
