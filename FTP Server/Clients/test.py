with open("client.py", "r") as file:
            data = file.read().encode("utf-8")
            # client.send("Start".encode("utf-8"))
            print("Data = ",data.decode("utf-8"))
            