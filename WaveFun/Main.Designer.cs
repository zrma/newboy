namespace WaveFun
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnGenerateWave = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnGenerateWave
            // 
            this.btnGenerateWave.Location = new System.Drawing.Point(12, 12);
            this.btnGenerateWave.Name = "btnGenerateWave";
            this.btnGenerateWave.Size = new System.Drawing.Size(241, 50);
            this.btnGenerateWave.TabIndex = 1;
            this.btnGenerateWave.Text = "Generate Sine Wave";
            this.btnGenerateWave.UseVisualStyleBackColor = true;
            this.btnGenerateWave.Click += new System.EventHandler(this.btnGenerateWave_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(265, 74);
            this.Controls.Add(this.btnGenerateWave);
            this.Name = "frmMain";
            this.Text = "Wave Generator";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGenerateWave;
    }
}

