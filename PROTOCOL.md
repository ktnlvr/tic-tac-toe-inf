# CLIENT -> SERVER
PONG

NEW
    name_len: int
    player_name: str
    game_id: int

PUT
    x: int
    y: int


# SERVER -> CLIENT
PING

BEGIN
    opponent_name: str

PUT
    x: int
    y: int

END
    you_win: bool
    x_a: int
    y_a: int 
    x_b: int
    y_b: int

