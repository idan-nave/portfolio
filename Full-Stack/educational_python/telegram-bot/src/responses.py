def handle_response(text: str) -> str:
    processed: str = text.lower()
    
    if 'hello' in processed:
        return 'hey there'

    if 'how are you' in processed:
        return 'pretty much okay'

    if 'where are you?' in processed:
        return 'im on a tree'
    
    return 'im both a bot and a banana'
