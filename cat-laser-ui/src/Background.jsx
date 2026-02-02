// src/Background.jsx
import React from 'react';

const orbs = [
  { size: 200, color: 'rgba(16,185,129,0.3)', top: '10%', left: '15%', delay: '0s' },
  { size: 150, color: 'rgba(14,165,233,0.25)', top: '60%', left: '25%', delay: '2s' },
  { size: 250, color: 'rgba(16,185,129,0.2)', top: '30%', left: '75%', delay: '4s' },
  { size: 180, color: 'rgba(14,165,233,0.3)', top: '75%', left: '60%', delay: '6s' },
];

export default function Background() {
  return (
    <div className="fixed inset-0 -z-10 overflow-hidden">
      {orbs.map((o, i) => (
        <div
          key={i}
          className="orb"
          style={{
            width: o.size,
            height: o.size,
            background: o.color,
            top: o.top,
            left: o.left,
            animationDelay: o.delay,
          }}
        />
      ))}
    </div>
  );
}
