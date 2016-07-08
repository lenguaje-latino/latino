Public Class Form1
    Private Sub ArchivoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ArchivoToolStripMenuItem.Click

    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load

    End Sub

    Private Sub FechaToolStripMenuItem_Click(sender As Object, e As EventArgs)

    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click
        SaveFileDialog1.ShowDialog()
        SaveFileDialog1.Filter = "|*.lat"
        SaveFileDialog1.Title = "Guardar como..."
        ' If (SaveFileDialog1.FileName) Then
        System.IO.File.Create(SaveFileDialog1.FileName).Dispose()
        ' End If
        '  If Not (SaveFileDialog1.FileName) Then
        '  Me.Close()
        '  End If
    End Sub

    Private Sub PegarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PegarToolStripMenuItem.Click
        RichTextBox1.Paste()
    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click
        Dim newform = New Form1
        newform.Text = "Latino Editor - Sin título"
        newform.Show()
    End Sub

    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click
        OpenFileDialog1.ShowDialog()
        OpenFileDialog1.Filter = "Código Latino|*.lat"
        OpenFileDialog1.Title = "Latino Editor"
        If (OpenFileDialog1.ShowDialog = DialogResult.OK) Then
            RichTextBox1.Text = My.Computer.FileSystem.ReadAllText(OpenFileDialog1.FileName)

        End If
        Me.Text = OpenFileDialog1.FileName
    End Sub

    Private Sub ImprimirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ImprimirToolStripMenuItem.Click
        PrintDialog1.ShowDialog()
    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Me.Close()
    End Sub

    Private Sub CortarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CortarToolStripMenuItem.Click
        RichTextBox1.Cut()
    End Sub

    Private Sub CopiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarToolStripMenuItem.Click
        RichTextBox1.Copy()
    End Sub

    Private Sub DeshacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DeshacerToolStripMenuItem.Click
        RichTextBox1.Undo()
    End Sub

    Private Sub RehacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RehacerToolStripMenuItem.Click
        RichTextBox1.Redo()
    End Sub

    Private Sub FuenteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FuenteToolStripMenuItem.Click
        FontDialog1.ShowDialog()
        RichTextBox1.Font = FontDialog1.Font
    End Sub

    Private Sub LimpiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LimpiarToolStripMenuItem.Click
        RichTextBox1.Clear()
    End Sub

    Private Sub SeleccionarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SeleccionarTodoToolStripMenuItem.Click
        RichTextBox1.SelectAll()
    End Sub

    Private Sub ImprimirFechaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ImprimirFechaToolStripMenuItem.Click
        RichTextBox1.Text = Date.Now
    End Sub

    Private Sub FormatoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FormatoToolStripMenuItem.Click

    End Sub


End Class
