USE itp_undefined;

CREATE TABLE IF NOT EXISTS template_gameLogs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    paddle1_x DOUBLE,
    paddle1_y DOUBLE,
    paddle2_x DOUBLE,
    paddle2_y DOUBLE,
    ball_x DOUBLE,
    ball_y DOUBLE,
    ball_vx DOUBLE,
    ball_vy DOUBLE,
    score1 INT,
    score2 INT,
    timestamp BIGINT
);
