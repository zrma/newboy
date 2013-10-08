//-----------------------------------------------------
// Main.cs
// Code for the main form of this app.
//
// Copyright (c) 2009 Dan Waters
// This code is provided AS-IS and is written by me,
// with no endorsement from Microsoft.
//-----------------------------------------------------

using System;
using System.Windows.Forms;
using System.Media;

namespace WaveFun
{
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
            cbWaveType.SelectedIndex = 0;
        }

        private void btnGenerateWave_Click(object sender, EventArgs e)
        {
            // Check the file is OK
            if (tbFileLocation.Text.IndexOf('(') >= 0)
            {
                MessageBox.Show("Please select a file first.");
                return;
            }

            // Set filepath
            string filePath = tbFileLocation.Text;

            // Instantiate wave generator
            WaveGenerator wave = new WaveGenerator(
                (WaveExampleType)cbWaveType.SelectedIndex, 
                sldFrequency.Value, 
                (double)(sldVolume.Value / 100.0f)
                );

            // Save to filepath
            wave.Save(filePath);            

            // Play the sound
            SoundPlayer player = new SoundPlayer(filePath);               
            player.Play();             
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            // Open a .wav save file dialog
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.AddExtension = true;
            sfd.DefaultExt = "wav";
            sfd.Filter = "WAV audio files (*.wav)|*.wav";

            if (sfd.ShowDialog() == DialogResult.OK)
            {
                btnGenerateWave.Enabled = true;
                tbFileLocation.Text = sfd.FileName;
            }
        }

        private void tbFrequency_Scroll(object sender, EventArgs e)
        {
            lblFrequency.Text = sldFrequency.Value.ToString();
        }

        private void sldVolume_Scroll(object sender, EventArgs e)
        {
            lblVolume.Text = sldVolume.Value.ToString() + "%";
        }
    }
}
