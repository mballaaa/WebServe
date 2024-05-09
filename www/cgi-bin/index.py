import sys

def count_lines():
    line_count = 0
    for line in sys.stdin:
        line_count += 1
    return line_count

def generate_html(line_count):
    html_content = f"""
    <!DOCTYPE html>
    <html>
    <head>
        <title>Line Count</title>
        <style>
            body {{
                font-family: Arial, sans-serif;
                margin: 0;
                padding: 0;
                background-color: #f0f0f0;
            }}
            .container {{
                width: 50%;
                margin: 50px auto;
                background-color: #fff;
                padding: 20px;
                border-radius: 10px;
                box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            }}
            h1 {{
                color: #333;
                text-align: center;
            }}
            p {{
                color: #666;
                text-align: center;
            }}
        </style>
    </head>
    <body>
        <div class="container">
            <h1>Line Count</h1>
            <p>Number of lines entered: {line_count}</p>
        </div>
    </body>
    </html>
    """
    return html_content

def main():
    line_count = count_lines()
    html_content = generate_html(line_count)
    print(html_content)

if __name__ == "__main__":
    main()