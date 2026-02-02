import React, { useState, useEffect } from 'react';

export default function App() {
  const [loading, setLoading] = useState(true);
  const [laserOn, setLaserOn] = useState(false);

  useEffect(() => {
    const t = setTimeout(() => setLoading(false), 3000);
    return () => clearTimeout(t);
  }, []);

  const sendCommand = (dir) => console.log('Move:', dir);

  const toggleLaser = () => {
    const newState = !laserOn;
    setLaserOn(newState);
    console.log('Laser is now:', newState ? 'ON' : 'OFF');
    // Example: You could send a fetch here to your Arduino if needed
    // fetch(`http://localhost:8080/laser?state=${newState ? 'on' : 'off'}`)
  };

  const arrowPanel = `
    w-64 sm:w-72 lg:w-80
    h-64 sm:h-72 lg:h-80
    bg-[#101229]/80 border border-green-400 border-opacity-30
    rounded-2xl p-4
    shadow-[0_0_10px_rgba(16,185,129,0.5)]
    flex items-center justify-center
  `;
  const videoPanel = `
    w-full max-w-[800px] aspect-video
    bg-[#101229]/80 border border-green-400 border-opacity-30
    rounded-2xl p-4
    shadow-[0_0_10px_rgba(16,185,129,0.5)]
    flex flex-col
  `;
  const arrowBtn = `
    w-16 h-16 sm:w-20 sm:h-20
    bg-[#101229]
    border-2 border-green-400 border-opacity-50
    rounded-lg
    shadow-[inset_0_0_6px_rgba(16,185,129,0.5)]
    hover:shadow-[0_0_15px_rgba(16,185,129,0.8)]
    hover:scale-110
    flex items-center justify-center
    text-lg sm:text-xl font-semibold text-green-400
    transition-all duration-300 ease-out
  `;

  const orbs = [
    { size: 300, color: 'rgba(16,185,129,0.15)', top: '15%', left: '10%', delay: '0s', duration: '14s' },
    { size: 250, color: 'rgba(16,185,129,0.1)',  top: '65%', left: '75%', delay: '3s', duration: '12s' },
    { size: 100, color: 'rgba(16,185,129,0.05)', top: '40%', left: '30%', delay: '1s', duration: '8s' },
    { size:  80, color: 'rgba(16,185,129,0.08)', top: '80%', left: '20%', delay: '4s', duration: '6s' },
  ];

  if (loading) {
    return (
      <div className="fixed inset-0 bg-[#0a0c18] flex items-center justify-center z-50">
        <div className="w-12 h-12 border-2 border-green-400 border-t-transparent rounded-full animate-spin" />
      </div>
    );
  }

  return (
    <>
      <style>{`
        @keyframes float {
          0%,100% { transform: translateY(0) scale(1); opacity:0.5; }
          50%      { transform: translateY(-10px) scale(1.05); opacity:0.7; }
        }
        .orb { position: absolute; border-radius: 50%; filter: blur(16px); }
        @keyframes heartbeat {
          0%,100% { transform: scale(1); box-shadow: 0 0 2px 1px rgba(16,185,129,0.6); }
          50%     { transform: scale(1.2); box-shadow: 0 0 4px 2px rgba(16,185,129,0.8); }
        }
        .heartbeat-glow { animation: heartbeat 2s ease-in-out infinite; }
      `}</style>

      <div className="relative w-full min-h-screen bg-[#0a0c18] overflow-hidden">
        <div className="fixed inset-0 -z-10 bg-gradient-to-br from-green-900 via-transparent to-green-900 opacity-10 transition-opacity duration-2000 ease-in-out" />
        {orbs.map((o,i) => (
          <div
            key={i}
            className="orb -z-10"
            style={{
              width: o.size, height: o.size, background: o.color,
              top: o.top, left: o.left,
              animation: `float ${o.duration} ease-in-out ${o.delay} infinite`
            }}
          />
        ))}

        <header className="fixed top-0 left-0 w-full flex justify-center py-4 z-10">
          <h1 className="text-3xl sm:text-4xl font-extrabold text-green-400 drop-shadow-lg">
            purrfectLaser
          </h1>
        </header>

        <main className="pt-20 px-4 md:px-8 lg:px-16 flex flex-col items-center gap-6 z-10 relative">
          
          <section className={videoPanel}>
            <div className="flex items-center space-x-2 mb-4">
              <span className="w-3 h-3 bg-green-400 rounded-full heartbeat-glow" />
              <span className="text-green-300 text-sm uppercase font-medium">
                Live Cam
              </span>
            </div>
            <div className="flex-1 bg-black rounded-lg overflow-hidden">
              <iframe
                src="http://localhost:8080"
                title="Live Camera Feed"
                className="w-full h-full"
                frameBorder="0"
              />
            </div>
          </section>

          <section className={arrowPanel}>
            <div className="grid grid-cols-3 grid-rows-3 gap-4 justify-items-center items-center">
              <div />
              <button onClick={() => sendCommand('UP')}    className={arrowBtn}>UP</button>
              <div />
              <button onClick={() => sendCommand('LEFT')}  className={arrowBtn}>LEFT</button>
              <div />
              <button onClick={() => sendCommand('RIGHT')} className={arrowBtn}>RIGHT</button>
              <div />
              <button onClick={() => sendCommand('DOWN')}  className={arrowBtn}>DOWN</button>
              <div />
            </div>
          </section>

          {/* Laser ON/OFF Toggle Button */}
          <section className="mt-6 flex items-center justify-center">
            <button
              onClick={toggleLaser}
              className={`
                px-6 py-3
                ${laserOn ? 'bg-green-500 text-black' : 'bg-black text-green-400'}
                border-2 border-green-400 border-opacity-50
                rounded-full font-semibold text-lg
                shadow-[inset_0_0_6px_rgba(16,185,129,0.4)]
                hover:shadow-[0_0_12px_rgba(16,185,129,0.6)]
                transition-all duration-300 ease-out
              `}
            >
              {laserOn ? 'Turn Laser OFF' : 'Turn Laser ON'}
            </button>
          </section>

        </main>
      </div>
    </>
  );
}
