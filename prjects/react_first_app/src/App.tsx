import React, { useState } from 'react';

// Define our types
type SquareValue = 'X' | 'O' | null;

interface SquareProps {
  value: SquareValue;
  onSquareClick: () => void;
  isWinning?: boolean;
}

interface BoardProps {
  xIsNext: boolean;
  squares: SquareValue[];
  onPlay: (nextSquares: SquareValue[]) => void;
}

function Square({ value, onSquareClick }: SquareProps): JSX.Element {
  return (
    <button className="square" onClick={onSquareClick}>
      {value}
    </button>
  );
}

function Board({ xIsNext, squares, onPlay }: BoardProps): JSX.Element {

  const boardSize = 3;
  const [winningLine, setWinningLine] = useState<number[]>([]);

  function handleClick(i: number): void {
    if (calculateWinner(squares) || squares[i]) {
      return;
    }
    const nextSquares = squares.slice();
    if (xIsNext) {
      nextSquares[i] = 'X';
    } else {
      nextSquares[i] = 'O';
    }
    onPlay(nextSquares);
  }

  const winner = calculateWinner(squares);
  let status: string;
  if (winner) {
    status = 'Winner: ' + winner.winner;
    setWinningLine(winner.line);
  } else {
    status = 'Next player: ' + (xIsNext ? 'X' : 'O');
    setWinningLine([]);
  }

  const renderBoard = () => {
    const boardRows = [];

    for(let row = 0; row < boardSize; row++){
      const squaresInRow = [];
      for(let col = 0; col < boardSize; col++){
        const index = row * boardSize + col;
        const isWinningSquare = winningLine.includes(index);

        squaresInRow.push(
          <Square 
            key={index}
            value={squares[index]}
            onSquareClick={() =>handleClick(index)}
            isWinning={isWinningSquare}
            />
        );
      }

      boardRows.push(
        <div key={row} className="board-row">
          {squaresInRow}
        </div>
      )
    }
    return boardRows;
  }

  return (
    <>
      <div className="status">{status}</div>
     {renderBoard()}
    </>
  );
}

export default function Game(): JSX.Element {
  const [history, setHistory] = useState<SquareValue[][]>([Array(9).fill(null)]);
  const [isReversed, setIsReversed] = useState<boolean>(false);
  const [currentMove, setCurrentMove] = useState<number>(0);
  const xIsNext: boolean = currentMove % 2 === 0;
  const currentSquares: SquareValue[] = history[currentMove];

  const toggleOrder = () => {
    setIsReversed(!isReversed);
  };

  function handlePlay(nextSquares: SquareValue[]): void {
    const nextHistory = [...history.slice(0, currentMove + 1), nextSquares];
    setHistory(nextHistory);
    setCurrentMove(nextHistory.length - 1);
  }

  function jumpTo(nextMove: number): void {
    setCurrentMove(nextMove);
  }

  const moves = history.slice(0,currentMove + 1).map((squares, move) => {
    let description: string;
    if (move > 0) {
      description = 'Go to move #' + move;
    } else {
      description = 'Go to game start';
    }
    return (
      <li key={move}>
        <button onClick={() => jumpTo(move)}>{description}</button>
      </li>
    );
  });

  return (
    <div className="game">
      <div className="game-board">
        <Board xIsNext={xIsNext} squares={currentSquares} onPlay={handlePlay} />
      </div>
      <div className="game-info">
        <h2>You are at current move #{currentMove}</h2>
        <button onClick={toggleOrder}>
            {isReversed ? 'Ascending' : 'Descending'};
        </button>
        <h3>History</h3>
        <ol className={`moves-list ${isReversed ? 'reversed' : ''}`}>
          {moves}
        </ol>

      </div>
    </div>
  );
}

function calculateWinner(squares: SquareValue[]): { winner: SquareValue; line: number[]} | null {
  const lines = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < lines.length; i++) {
    const [a, b, c] = lines[i];
    if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
      return { winner:squares[a], line: lines[i]};
    }
  }
  return null;
}